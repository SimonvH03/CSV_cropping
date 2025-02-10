#!/bin/bash

# Define file paths
SOURCE="code/config_default.h"
DESTINATION="config.h"

# Check if the source file exists
if [ ! -f "$SOURCE" ]; then
	echo "❌ Error: Source file '$SOURCE' not found! You really have to stop touching the wrong files..."
	exit 1
fi

# Restore the default configuration
cp "$SOURCE" "$DESTINATION"

# Verify success
if [ $? -eq 0 ]; then
	echo "✅ Successfully restored config.h default values"
else
	echo "❌ Failed to recover config.h... crazy stuff"
	exit 1
fi
