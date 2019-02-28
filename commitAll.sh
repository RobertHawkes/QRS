#!/bin/sh
git checkout master
git add *
echo 'Please enter a commit message:'
read commitMessage
git commit -am \"$commitMessage\"
echo Commited to branch master with commit message: $commitMessage
read