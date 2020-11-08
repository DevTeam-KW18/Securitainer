<?php

$con=mysqli_connect("localhost","s2moon98","Answldms98!","db");
	if(mysqli_connect_errno())
	{
		echo "Faild to connect to MySQL:".mysqli_connect_error();
	}

         
	header("Content-Type:text/html;charset=utf8");   
	mysqli_query($con, "set session character_set_connection=utf8;");
	mysqli_query($con, "set session character_set_results=utf8;");
	mysqli_query($con, "set session character_set_client=utf8;");
  	$id_code=$_GET['id_code'];
	$depart=$_GET['depart'];
	header("Content-Type:text/html;charset=utf8");

	$sql = "UPDATE container SET depart='".$depart."' where id_code='".$id_code."'";

	mysqli_query($con,$sql);
	mysqli_close($con);
        echo("<meta http-equiv='Refresh' content='1; URL=basic.html?type=2'>");

?>

