#! /bin/bash
echo Détruire toutes les VM
cd 41VM1/
vagrant destroy &
cd ..
cd 42VM2/
vagrant destroy &
cd ..
cd 43VM3/
vagrant destroy &
cd ..
cd 61VM1-6/
vagrant destroy &
cd ..
cd 62VM2-6/
vagrant destroy &
cd ..
cd 63VM3-6/
vagrant destroy &
cd ..
