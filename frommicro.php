<?php
//trigBoard ArduCam PHP CODE
//RELEASED 3/29/18
//Make sure this is in a folder on the server, then add another folder in there called "images" - that is where this file will store everything


foreach($_REQUEST as $key => $value){// I pass the filename in the URL, so we pull that at in the data variable
if($key =="data"){
$fileTitle = $value;
}
}//for each

//when doing a POST, we can check for the "value" tag we gave it in the Arduino code
$data = $_POST['value'];

//this part took the longest time to figure out!!

// first we need to separate each data byte out, so since we delimited with commas, this makes it easy
$txt = explode(',',$data);//this takes the data paket and splits into an array stored in txt split by commas
$count = count($txt);//get the number of elements in the array
$dataTobeWritten = "";//new string to use to store
for ($x = 0; $x < ($count-1); $x++){//sweep through the array of bytes and create the packet to be written
$dataTobeWritten .= chr($txt[$x]);//just add each byte onto the string
}

$fileToWrite = 'images/' . $fileTitle;//this is the file we'll write to - file title came in with the URL

$myfile = fopen($fileToWrite, "a") or die("Unable to open file!");//open up the file

fwrite($myfile, $dataTobeWritten);//this appends the data we received to the file, since we call this multiple times, need to append
fclose($myfile);//done
echo filesize($fileToWrite);// send back the size of the file to compare to
?>