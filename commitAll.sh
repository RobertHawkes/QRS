#!/bin/sh
git checkout master
git add *
echo 'Please enter a commit message:'
read commitMessage
git commit -m "$commitMessage"
echo Commited to branch master with commit message: $commitMessage
sleep 3