<?php
		$con = mysqli_connect("localhost","s2moon98","Answldms98!","db");
	
		if(mysqli_connect_errno())
		{
			echo "Faild to eonnect to MySQL: " . mysqli_connect_error();
		}
		
	$id = $_GET['id'];
	$pwd = $_GET['pwd'];
        $type= $_GET['type'];
	$sql = "insert into db.user(id, pwd,type) values('$id','$pwd','$type')";
	mysqli_query($con, $sql);

	mysqli_close($con);

	 echo("<meta http-equiv='Refresh' content='1; URL=index.html'>");


?>
			


