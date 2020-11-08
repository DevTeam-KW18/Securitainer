<?php 
  include 'inc_head.php';
?>
<!doctype html>
<html lang="ko">
  <head>
    <meta charset="utf-8">
    <title>LOGIN_RESULT</title>
  </head>
  <body>
    <?php
      
        $con=mysqli_connect("localhost","s2moon98","Answldms98!","db");
	
        $username = $_POST[ 'username' ];
	$pwd = $_POST[ 'pwd' ];
	$sql = "SELECT id , pwd , type FROM db.user WHERE id='$username'AND pwd='$pwd'";
	$result= $con->query($sql);	
	if ( $result->num_rows>0 ) {
		$_SESSION[ 'username' ] = $username;
		$ary = $result->fetch_assoc();
		$result_type = $ary['type'];
	 echo("<meta http-equiv='Refresh' content='1; URL=basic.html?type={$result_type}'>");
	} else {
		echo '<script>alert("존재하지 않는 계정입니다");</script>';

		echo("<meta http-equiv='Refresh' content='0; URL=login.html'>");

        }
      
  $con->close();
?>
  </body>
</html>
