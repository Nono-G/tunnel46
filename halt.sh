#! /bin/bash
echo Lancer toutes les VM
cd 41VM1/
vagrant halt &
cd ..
cd 42VM2/
vagrant halt &
cd ..
cd 43VM3/
vagrant halt &
cd ..
cd 61VM1/
vagrant halt &
cd ..
cd 62VM2/
vagrant halt &
cd ..
cd 63VM3/
vagrant halt &
cd ..
