<?php
    session_start();
    if(isset($_GET["Ssn"]) && !empty(trim($_GET["Ssn"]))){
		$_SESSION["Ssn"] = $_GET["Ssn"];
    }
    if(isset($_GET["Dname"]) && !empty(trim($_GET["Dname"]))){
		$_SESSION["Dname"] = $_GET["Dname"];
	}

    require_once "config.php";
	
	// Delete an Employee's record after confirmation
	if ($_SERVER["REQUEST_METHOD"] == "POST") {
        if(isset($_SESSION["Ssn"]) && !empty($_SESSION["Ssn"]) && isset($_SESSION["Dname"]) && !empty($_SESSION["Dname"])){ 
            $Ssn = $_SESSION['Ssn'];
            $Dname = $_SESSION['Dname'];

            // Prepare a delete statement
            $sql = "DELETE FROM `DEPENDENT`WHERE Dependent_name = ? AND Essn = ?";

            if($stmt = mysqli_prepare($link, $sql)){
            // Bind variables to the prepared statement as parameters
                mysqli_stmt_bind_param($stmt, "si", $param_Dependent_name, $param_Ssn);

                // Set parameters
                $param_Dependent_name = $Dname;
                $param_Ssn = $Ssn;
        
                // Attempt to execute the prepared statement
                if(mysqli_stmt_execute($stmt)){
                    // Records deleted successfully. Redirect to landing page
                    header("location: index.php");
                    exit();
                } else{
                    echo "Error deleting the dependent";
                }
            }
            // Close statement
            mysqli_stmt_close($stmt);
            // Close connection
            mysqli_close($link);
        }
	}else{
		// Check existence of id parameter
		if(empty(trim($_GET["Ssn"]))){
			// URL doesn't contain id parameter. Redirect to error page
			header("location: error.php");
			exit();
		}
	}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Delete Dependent</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.css">
    <style type="text/css">
        .wrapper{
            width: 500px;
            margin: 0 auto;
        }
    </style>
</head>
<body>
    <div class="wrapper">
        <div class="container-fluid">
            <div class="row">
                <div class="col-md-12">
                    <div class="page-header">
                        <h1>Delete Dependent</h1>
                    </div>
                    <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post">
                        <div class="alert alert-danger fade in">
                            <input type="hidden" name="Dname" value="<?php echo ($_SESSION["Dname"]); ?>"/>
                            <p>Are you sure you want to delete the record for <?php echo ($_SESSION["Dname"]); ?>?</p><br>
                                <input type="submit" value="Yes" class="btn btn-danger">
                                <a href="viewDependents.php?Ssn=<?php echo $_GET["Ssn"];?>" class="btn btn-default">No</a>
                            </p>
                        </div>
                    </form>
                </div>
            </div>        
        </div>
    </div>
</body>
</html>