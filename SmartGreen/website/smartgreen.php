<?php
/**
 * CAMPETTO SPECIALITA' ESPERTO DEL COMPUTER - E/G AGESCI LAZIO
 */

    $mysql_host = "localhost";
    $mysql_user = "user";
    $mysql_password = "password";
    $mysql_database = "arduino_database";

    // mysql connection
    $conn = new mysqli($mysql_host, $mysql_user, $mysql_password, $mysql_database);
    if ($conn->connect_error) {
        die("mysqli connection error");
    }

    // retrieve data
    // sql query
    $sql = "SELECT * FROM measures WHERE id=1";
    $result = mysqli_query($conn, $sql);
    if ($result == false) {
        die("mysqli error");
    }
    $row = $result->fetch_row();
    $tempA =  (string)$row["tempA"];
    $tempB =  (string)$row["tempB"];
    $tempC =  (string)$row["tempC"];
    $moistA = (string)$row["moistA"];
    $moistB = (string)$row["moistB"];
    $moistC = (string)$row["moistC"];

    $conn->close();
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta http-equiv="content-type" content="text/html; charset=UTF-8">
    <meta charset="utf-8">
    <title>GamerLand - online store</title>
    <meta name="generator" content="Bootply" />
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
    <link href="css/bootstrap.min.css" rel="stylesheet">
    <!--[if lt IE 9]>
    <script src="//html5shim.googlecode.com/svn/trunk/html5.js"></script>
    <![endif]-->
    <link href="css/styles.css" rel="stylesheet">
</head>
<body>

<div class="navbar navbar-default">
    <div class="container">
        <a class="navbar-brand" href="#">GamerLand Green Hacking</a>
    </div>
</div>

<div class="jumbotron text-center">
    <h3>SERRA A</h3>
    <hr>
    <p><h2>TEMPERATURA: <?php echo $tempA ?></h2></p>
    <p><h2>UMIDITA' TERRENO: <?php
                                switch ($moistA) {
                                    case "G":
                                        echo "OTTIMALE";
                                        break;
                                    case "Y":
                                        echo "NORMALE (irrigare se possibile)";
                                        break;
                                    case "R":
                                        echo "NECESSARIO IRRIGARE";
                                        break;
                                }
                           ?>
    </h2> </p>
    <hr>
</div>

<div class="jumbotron text-center">
    <h3>SERRA A</h3>
    <hr>
    <p><h2>TEMPERATURA: <?php echo $tempB ?></h2></p>
    <p><h2>UMIDITA' TERRENO: <?php
        switch ($moistB) {
            case "G":
                echo "OTTIMALE";
                break;
            case "Y":
                echo "NORMALE (irrigare se possibile)";
                break;
            case "R":
                echo "NECESSARIO IRRIGARE";
                break;
        }
        ?>
    </h2> </p>
    <hr>
</div>

<div class="jumbotron text-center">
    <h3>SERRA A</h3>
    <hr>
    <p><h2>TEMPERATURA: <?php echo $tempC ?></h2></p>
    <p><h2>UMIDITA' TERRENO: <?php
        switch ($moistC) {
            case "G":
                echo "OTTIMALE";
                break;
            case "Y":
                echo "NORMALE (irrigare se possibile)";
                break;
            case "R":
                echo "NECESSARIO IRRIGARE";
                break;
        }
        ?>
    </h2> </p>
    <hr>
</div>

