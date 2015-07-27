#!/bin/bash

HOME=".."
PROJECTS="test"
TEST="test"

MAKE_COMMAND="make BOARD=openmote-cc2538"
CLEAN_COMMAND="make BOARD=openmote-cc2538 clean"

cd $HOME
HOME=$(pwd)

cd $PROJECTS

ERROR=false

for PROJECT in *; do
    if [ -d "$PROJECT" ] && [ "$ERROR" == false ]; then
        
        cd $PROJECT
        
        echo -ne "Cleaning $PROJECT..."
        OUTPUT=$($CLEAN_COMMAND 2>&1)
        echo -e "ok!"
        
        echo -ne "Building $PROJECT..."
        OUTPUT=$($MAKE_COMMAND 2>&1) 
        
        if [[ $OUTPUT == *rror* ]]; then
            echo -e "$OUTPUT" > $HOME/$TEST/$PROJECT.log
            echo -e "error!"
            ERROR=true
        else
            echo -e "ok!"
            ERROR=false
        fi
        
        OUTPUT=$($CLEAN_COMMAND 2>&1)
        
        cd $HOME/$TEST
    fi
done

if [[ "$ERROR" == true ]]; then
    echo "Tests finished with errors!"
    exit 1
else
    echo "Tests finished successfully!"
    exit 0
fi

