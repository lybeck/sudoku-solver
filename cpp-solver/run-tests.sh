#!/bin/bash

function rm_if_exists() {
	if [ -f $1 ]; then
        	rm $1
	fi
}

out_dir=output
sudoku_dir=test-files/fpt09
times_file=times.out
output_file=output.out

mkdir -p $out_dir

rm_if_exists "$out_dir/$times_file"
rm_if_exists "$out_dir/$output_file"

sout="$out_dir/$output_file"
eout="$out_dir/$times_file"
tmp="$out_dir/tmp.txt"

for f in $sudoku_dir/*.sudoku; do

	echo $f

	for of in $sout $eout ; do
		echo "" >> $of
		echo "Input file: $f" >> $of
                echo "" >> $of
	done

	{ time ./sudoku-release $f ;} 1>> $sout 2> $tmp

	grep "^user" $tmp >> $eout

        for of in $sout $eout ; do
                echo "" >> $of
                echo "=========================================================" >> $of
        done
done

rm_if_exists $tmp
