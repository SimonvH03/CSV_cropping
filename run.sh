#!/bin/bash

echo "🔄 Cleaning and recompiling the project..."

# Remake to clean and compile
make -C ./code re -s

# Check if compilation was successful
if [ ! -f "./code/autocrop" ]; then
	echo "❌ Compilation failed! Please restore Makefile and source code, don't touch it again"
	exit 1
fi

echo "✅ Compilation successful!"

# Run the program and catch the exit/return code
./code/autocrop
exit_code=$?

echo "Program completed with exit code $exit_code"

# Handle different exit codes
case $exit_code in
	255)
		echo "❌ Error: A critical failure occurred, probably memory related"
		;;
	0)
		echo "✅ Program completed successfully!"
		;;
	1)
		echo "⚠️  Error: Program Failed, please revise or restore Configuration"
		;;
	*)
		echo "🔥 Unknown 🔥 error 🔥 code 🔥 ($exit_code) 🔥 Freak 🔥 out 🔥"
		;;
esac

# Propagate the exit code
exit $exit_code
