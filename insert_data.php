<?php
		$con = mysqli_connect("localhost","s2moon98","Answldms98!","db");
	
		if(mysqli_connect_errno())
		{
			echo "Faild to eonnect to MySQL: " . mysqli_connect_error();
		}
		
	$id = $_GET['id'];
	$pwd = $_GET['pwd'];
	$type= $_GET['type'];


	 $sql = "SELECT * FROM user WHERE id='$id'";
	$result = mysqli_query($con, $sql);

	  if( mysqli_num_rows($result) == 0) {
		$sql = "insert into db.user(id, pwd,type) values('$id','$pwd','$type')";
		mysqli_query($con, $sql);
		 echo("<meta http-equiv='Refresh' content='1; URL=index.html'>");

	  }
	 else
	 {
		 echo '<script>alert("이미 존재하는 아이디 입니다");</script>';	
		  echo("<meta http-equiv='Refresh' content='1; URL=join.html'>");

	 }

	mysqli_close($con);


?>
	


