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
	$item=$_GET['item'];
	$owner=$_GET['owner'];
	$depart=0;
	header("Content-Type:text/html;charset=utf8");
	$sql="insert into db.container(id_code,item,owner,depart) values('$id_code','$item','$owner','$depart')";
	mysqli_query($con,$sql);
	mysqli_close($con);
	echo("<meta http-equiv='Refresh' content='1; URL=basic.html?type=1'>");
?>
