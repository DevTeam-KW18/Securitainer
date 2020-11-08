<?php
      $con = mysqli_connect("localhost","s2moon98","Answldms98!","db");


        $id_code = $_GET['id_code'];
        $temp = $_GET['temp'];
        $humi = $_GET['humi'];
        $gas = $_GET['gas'];
        $gps = $_GET['gps'];


        $sql = "SELECT * FROM measures WHERE id_code ='$id_code'";
        $result = mysqli_query($con, $sql);

        $select_sql = "select * from container where id_code = '{$id_code}'";
        $select_result = mysqli_query($con, $select_sql);
        $select_row = mysqli_fetch_array($select_result);
        $item = $select_row['item'];


        if( mysqli_num_rows($result) > 0) {

                 $sql1 = "update measures set time=CURRENT_TIMESTAMP, item='$item', temp='$temp', humi='$humi', gas='$gas', gps='$gps' where id_code='$id_code'";
                 mysqli_query($con, $sql1);
                 echo "abcd";
        }
        else
        {
                $sql2 = "INSERT INTO measures(id_code, time, item, temp, humi, gas, gps) VALUES ('$id_code',CURRENT_TIMESTAMP,'$item','$temp','$humi','$gas','$gps')";
                mysqli_query($con, $sql2);
        }

      mysqli_close($con);

     // echo ("<meta http-equiv='Refresh' content='1; URL=h_index_test.html'>");

?>
~

