#!/bin/bash

echo "🔄 Cleaning and recompiling autocrop..."

# Remake to clean and compile
make -C ./code re -s

# Check if compilation was successful
if [ $? -ne 0 ]; then
	echo "❌ Compilation failed! Please restore Makefile and source code, don't touch it again"
	exit 1
fi

echo "✅ Compilation successful!"
echo "Output below produced by Autocrop"
echo "================================================================================"

# Run the program and catch the exit/return code
./code/autocrop
exit_code=$?

echo "================================================================================"
echo "Output below produced by run.sh"
echo "📌 Autocrop completed with exit code $exit_code"

# Handle different exit codes
case $exit_code in
	255)
		echo "❌ Error: A critical failure occurred, probably memory related"
		;;
	0)
		echo "✅ Autocrop completed successfully!"
		;;
	1)
		echo "⚠️  Error: Autocrop Failed, please revise or restore Configuration"
		;;
	*)
		echo "🔥 Unknown 🔥 error 🔥 code 🔥 ($exit_code) 🔥 Freak 🔥 out 🔥"
		;;
esac

# Propagate the exit code
exit $exit_code
