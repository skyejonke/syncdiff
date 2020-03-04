#!/bin/bash
HEAD=/tmp
mkdir $HEAD/Notes
mkdir $HEAD/Notes/.stversions
echo "Test Test Test \n Test" > $HEAD/Notes/test.md
echo "Test t test \n Test" > $HEAD/Notes/.stversions/test~2020.md
echo "No Source \n Found" > $HEAD/Notes/.stversions/noSource~2020.md
