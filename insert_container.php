<?php
		$con = mysqli_connect("localhost","s2moon98","Answldms98!","db");
	
		if(mysqli_connect_errno())
		{
			echo "Faild to eonnect to MySQL: " . mysqli_connect_error();
		}
		
	$id_code = $_GET['id_code'];
	$gps = $_GET['gps'];
	$item = $_GET['item'];
	$temp = $_GET["temp"];
	$gas = $_GET["gas"];
	$humi = $_GET["humi"];

	$sql = "insert into db.container(id_code, gps, item, temp, gas, humi) values('$id_code','$gps', '$item', $temp, $gas, $humi)";
	mysqli_query($con, $sql);

	mysqli_close($con);

?>
			


