<?php
      $con = mysqli_connect("localhost","s2moon98","Answldms98!","db");


	$id_code = $_GET['id_code'];
	$time = $_GET['time'];
	$owner = $_GET['owner'];
	$item = $_GET['item'];
	$temp = $_GET['temp'];
	$humi = $_GET['humi'];
	$gas = $_GET['gas'];
	$gps = $_GET['gps'];

      $sql = "update test set time=CURRENT_TIMESTAMP, owner='$owner', item='$item', temp='$temp', humi='$humi', gas='$gas', gps='$gps' where id_code='$id_code'";
      mysqli_query($con, $sql);

      mysqli_close($con);

     // echo ("<meta http-equiv='Refresh' content='1; URL=h_index_test.html'>");

?>
