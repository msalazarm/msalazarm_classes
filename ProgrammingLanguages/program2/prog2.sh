#!/bin/sh
# Name: Marco Salazar, Date: 9/9/2020

prints()
{
 echo "Not "
}
if prints && [[ 0 = 1 ]];
then
 echo ""
fi
echo "If there is a not above then the prints function works. real test starts below"
echo ""

if [[ 0 = 1 ]] && prints; 
then
   echo ""
fi
echo "Short Circuit Evaluation"
