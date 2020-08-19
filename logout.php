<?php 
  include 'inc_head.php';
?>
<!doctype html>
<html lang="ko">
  <head>
    <meta charset="utf-8">
    <title>PHP</title>
  </head>
  <body>
    <?php
      if ( $jb_login ) {
        session_destroy();
	echo '<h1>로그아웃 하였습니다.</h1>';
	  echo("<meta http-equiv='Refresh' content='1; URL=index.html'>");

      } else {
        echo '<h1>로그인 상태가 아닙니다.</h1>';
      }
    ?>
  </body>
</html>
