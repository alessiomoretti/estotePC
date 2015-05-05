<?php
/**
 * CAMPETTO SPECIALITA' ESPERTO DEL COMPUTER - E/G AGESCI LAZIO
 */

if (isset($_POST['temp'])) {
    $tempA = htmlspecialchars($_POST['tempA']);
    $tempA = (double)$tempA;
    $tempB = htmlspecialchars($_POST['tempB']);
    $tempB = (double)$tempB;
    $tempC = htmlspecialchars($_POST['tempC']);
    $tempC = (double)$tempC;

    $moistA = htmlspecialchars($_POST['moistA']);
    $moistA = (double)$moistA;
    $moistB = htmlspecialchars($_POST['moistB']);
    $moistB = (double)$moistB;
    $moistC = htmlspecialchars($_POST['moistC']);
    $moistC = (double)$moistC;

    $mysql_host = "localhost";
    $mysql_user = "user";
    $mysql_password = "password";
    $mysql_database = "arduino_database";

    // mysql connection
    $conn = new mysqli($mysql_host, $mysql_user, $mysql_password, $mysql_database);
    if ($conn->connect_error) {
        die("mysqli connection error");
    }

    // sql query
    $sql = "UPDATE measures SET tempA =  ".$tempA.",
                                tempB =  ".$tempB.",
                                tempC =  ".$tempC.",
                                moistA = ".$moistA.",
                                moistB = ".$moistB.",
                                moistC = ".$moistC."
                                WHERE id = 1";
    echo $sql;
    if (mysqli_query($conn, $sql)) {
        echo "Record update successfully";
    } else {
        echo "Error: " . $sql . "<br>" . mysqli_error($conn);
    }

    mysqli_close($conn);

}


