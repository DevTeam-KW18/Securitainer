<?php
      $con = mysqli_connect("localhost","s2moon98","Answldms98!","db");
   
      if(mysqli_connect_errno())
      {
         echo "Faild to eonnect to MySQL: " . mysqli_connect_error();
      }
      
   $num = $_GET['num'];

   $sql = "insert into db.inotest(num) values('$num')";
   mysqli_query($con, $sql);

   mysqli_close($con);

?>
