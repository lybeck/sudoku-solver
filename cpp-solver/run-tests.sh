#!/bin/bash

function rm_if_exists() {
	if [ -f $1 ]; then
        	rm $1
	fi
}

if [ $# = 0 ]; then
	echo "No arguments found!"
	echo "The argument(s) should be the files to run tests for."
	echo "  Example: $0 test-files/fpt09/*.sudoku"
	exit 1
fi

out_dir=output
times_file=times.out
output_file=output.out

mkdir -p $out_dir

rm_if_exists "$out_dir/$times_file"
rm_if_exists "$out_dir/$output_file"

sout="$out_dir/$output_file"
eout="$out_dir/$times_file"
tmp="$out_dir/tmp.txt"

format="Time elapsed: %E (%e seconds)"

# timeout in seconds
timeout=3600

for f in $@; do

	echo $f

	for of in $sout $eout ; do
		echo "" >> $of
		echo "Input file: $f" >> $of
                echo "" >> $of
	done

	{ timeout $timeout time -f"$format" ./sudoku-release $f ;} 1>> $sout 2> $tmp

	if [ $? = 0 ]; then
		cat $tmp >> $eout
	else
		echo "Timed out after $timeout seconds..." >> $eout
	fi

        for of in $sout $eout ; do
                echo "" >> $of
                echo "=========================================================" >> $of
        done
done

rm_if_exists $tmp
