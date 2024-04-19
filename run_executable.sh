#!/bin/bash
#thanks chat gpt very cool (this file was mostly created by chatgpt3.5)
#you need bc installed
# Define output directories

# Define output directories
OUTPUT_DIR="output"

# Define the paths to the executable files
EXEC_DEV="./main_dev"
EXEC_O1="./main_o1"
EXEC_O2="./main_o2"
EXEC_O3="./main_o3"
EXEC_LTO="./main_lto"

# Calculate mean from a single text file
calculate_mean() {
	local file="$1"
	local total=0
	local count=0
	# Read numbers from file and compute sum
	while IFS= read -r number; do
		total=$(bc -l <<<"$total + $number")
		count=$((count + 1))
	done <"$file"
	# Compute mean
	if ((count > 0)); then
		local mean=$(bc -l <<<"$total / $count")
		echo "Mean from $file: $mean"
	else
		echo "No numbers found in $file."
	fi
}

# Run each executable 100 times and record output
for i in {1..50}; do
	echo "Running $EXEC_DEV - Iteration $i"
	$EXEC_DEV >>"$OUTPUT_DIR/output_dev.txt" &
	pids[0]=$!

	echo "Running $EXEC_O1 - Iteration $i"
	$EXEC_O1 >>"$OUTPUT_DIR/output_o1.txt" &
	pids[1]=$!

	echo "Running $EXEC_O2 - Iteration $i"
	$EXEC_O2 >>"$OUTPUT_DIR/output_o2.txt" &
	pids[2]=$!

	echo "Running $EXEC_O3 - Iteration $i"
	$EXEC_O3 >>"$OUTPUT_DIR/output_o3.txt" &
	pids[3]=$!

	echo "Running $EXEC_LTO - Iteration $i"
	$EXEC_LTO >>"$OUTPUT_DIR/output_lto.txt" &
	pids[4]=$!

	# Wait for all processes to finish
	for pid in "${pids[@]}"; do
		wait "$pid"
	done
done

# Print confirmation message
echo "Executables run 100 times each, and output recorded in $OUTPUT_DIR directory."

# Calculate mean for each text file
for file in "$OUTPUT_DIR"/*.txt; do
	calculate_mean "$file"
done
