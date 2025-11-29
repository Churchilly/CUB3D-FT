#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Get executable path from argument or use default
EXECUTABLE="${1:-./cub3D}"

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo -e "${RED}Error: Executable not found: $EXECUTABLE${NC}"
    echo "Usage: $0 [path_to_executable] [--no-valgrind]"
    echo "Example: $0 ./cub3D"
    echo "Example: $0 /path/to/your/cub3D --no-valgrind"
    exit 1
fi

# Check for --no-valgrind flag
USE_VALGRIND=1
if [[ "$2" == "--no-valgrind" ]] || [[ "$1" == "--no-valgrind" ]]; then
    USE_VALGRIND=0
fi

# Check if valgrind is available
if [ $USE_VALGRIND -eq 1 ]; then
    if ! command -v valgrind &> /dev/null; then
        echo -e "${YELLOW}Warning: valgrind not found, running without memory checks${NC}"
        echo -e "${YELLOW}Install valgrind with: sudo apt-get install valgrind${NC}"
        USE_VALGRIND=0
    fi
fi

echo "Using executable: $EXECUTABLE"
if [ $USE_VALGRIND -eq 1 ]; then
    echo -e "${BLUE}Valgrind: ENABLED (memory leak detection)${NC}"
else
    echo -e "${YELLOW}Valgrind: DISABLED (faster but no memory checks)${NC}"
fi
echo ""

# Counter for tests
total_tests=0
passed_tests=0
failed_tests=0
memory_leaks=0

echo "=================================="
echo "   INVALID MAP TESTS FOR CUB3D"
echo "=================================="
echo ""

# Test each invalid map
for map in test_maps/invalid/*.cub test_maps/invalid/*.cu; do
    if [ -f "$map" ]; then
        total_tests=$((total_tests + 1))
        filename=$(basename "$map")

        has_error=0
        has_leak=0
        exit_code=0

        if [ $USE_VALGRIND -eq 1 ]; then
            # Run with valgrind
            valgrind_output=$(valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=42 "$EXECUTABLE" "$map" 2>&1)
            valgrind_exit=$?

            # Extract program output (everything before "==" lines which are valgrind's)
            output=$(echo "$valgrind_output" | grep -v "^==" | grep -v "^--")

            # Check exit code (42 means valgrind detected error, otherwise it's program's exit code)
            if [ $valgrind_exit -eq 42 ]; then
                # Valgrind detected memory error, but check if program also exited with error
                program_exited_with_error=$(echo "$output" | grep -q "Error" && echo 1 || echo 0)
                if [ $program_exited_with_error -eq 1 ]; then
                    has_error=1
                fi
                has_leak=1
            else
                # No valgrind error, check program behavior
                exit_code=$valgrind_exit
                if [ $exit_code -ne 0 ] && echo "$output" | grep -q "Error"; then
                    has_error=1
                fi
            fi

            # Check for memory leaks in valgrind output
            if echo "$valgrind_output" | grep -q "definitely lost:"; then
                lost_bytes=$(echo "$valgrind_output" | grep "definitely lost:" | head -1 | awk '{print $4}')
                if [ "$lost_bytes" != "0" ]; then
                    has_leak=1
                fi
            fi

            if echo "$valgrind_output" | grep -q "indirectly lost:"; then
                indirect_bytes=$(echo "$valgrind_output" | grep "indirectly lost:" | head -1 | awk '{print $4}')
                if [ "$indirect_bytes" != "0" ]; then
                    has_leak=1
                fi
            fi

            if echo "$valgrind_output" | grep -q "still reachable:"; then
                reachable_bytes=$(echo "$valgrind_output" | grep "still reachable:" | head -1 | awk '{print $4}')
                if [ "$reachable_bytes" != "0" ]; then
                    has_leak=1
                fi
            fi

        else
            # Run without valgrind
            output=$("$EXECUTABLE" "$map" 2>&1)
            exit_code=$?

            if [ $exit_code -ne 0 ] && echo "$output" | grep -q "Error"; then
                has_error=1
            fi
        fi

        # Evaluate test result
        if [ $has_error -eq 1 ] && [ $has_leak -eq 0 ]; then
            echo -e "${GREEN}✓${NC} $filename - ${GREEN}PASS${NC}"
            passed_tests=$((passed_tests + 1))
        elif [ $has_error -eq 1 ] && [ $has_leak -eq 1 ]; then
            echo -e "${YELLOW}⚠${NC} $filename - ${YELLOW}LEAK${NC} (correct error but memory leak detected)"
            memory_leaks=$((memory_leaks + 1))
            if [ $USE_VALGRIND -eq 1 ]; then
                echo -e "${YELLOW}  Memory leak details:${NC}"
                echo "$valgrind_output" | grep -A 3 "LEAK SUMMARY" | sed 's/^/  /'
            fi
        else
            echo -e "${RED}✗${NC} $filename - ${RED}FAIL${NC}"
            echo "  Expected: Error message and non-zero exit code"
            echo "  Got: Exit code $exit_code"
            echo "  Output: $output"
            failed_tests=$((failed_tests + 1))
        fi
    fi
done

echo ""
echo "=================================="
echo "           TEST SUMMARY"
echo "=================================="
echo -e "Total tests:  $total_tests"
echo -e "${GREEN}Passed:       $passed_tests${NC}"
if [ $USE_VALGRIND -eq 1 ]; then
    echo -e "${YELLOW}Memory leaks: $memory_leaks${NC}"
fi
echo -e "${RED}Failed:       $failed_tests${NC}"
echo "=================================="

if [ $failed_tests -eq 0 ] && [ $memory_leaks -eq 0 ]; then
    echo -e "${GREEN}All tests passed with no memory leaks!${NC}"
    exit 0
elif [ $failed_tests -eq 0 ] && [ $memory_leaks -gt 0 ]; then
    echo -e "${YELLOW}All tests passed but memory leaks detected!${NC}"
    echo -e "${YELLOW}Fix memory leaks before submission.${NC}"
    exit 1
else
    echo -e "${RED}Some tests failed!${NC}"
    exit 1
fi
