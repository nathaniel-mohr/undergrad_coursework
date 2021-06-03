<?php
	session_start();	
// Include config file
    require_once "config.php";
    

$Dependent_name = $Sex = $Bdate = $Relationshp = "";
$Dependent_name_err = $Sex_err = $Bdate_err = $Relationshp_err = "";
 
// Form default values

if(isset($_GET["Ssn"]) && !empty(trim($_GET["Ssn"])) && isset($_GET["Dname"]) && !empty(trim($_GET["Dname"]))){
    $_SESSION["Ssn"] = $_GET["Ssn"];
    $_SESSION["Dname"] = $_GET["Dname"];

    // Prepare a select statement
    $sql1 = "SELECT * FROM DEPENDENT WHERE Dependent_name = ? AND Essn = ?";

    if($stmt1 = mysqli_prepare($link, $sql1)){
        // Bind variables to the prepared statement as parameters
        mysqli_stmt_bind_param($stmt1, "si", $param_Dependent_name, $param_Ssn);      
        // Set parameters
        $param_Dependent_name = trim($_GET["Dname"]);
        $param_Ssn = trim($_GET["Ssn"]);

        // Attempt to execute the prepared statement
        if(mysqli_stmt_execute($stmt1)){
            $result1 = mysqli_stmt_get_result($stmt1);
            if(mysqli_num_rows($result1) > 0){

                $row = mysqli_fetch_array($result1);

                $Dependent_name = $row['Dependent_name'];
                $Sex = $row['Sex'];
                $Bdate = $row['Bdate'];
                $Relationship = $row['Relationship'];
            }
        }
    }
}
 

if($_SERVER["REQUEST_METHOD"] == "POST"){

    $Ssn = $_SESSION["Ssn"];
    $Dname = $_SESSION["Dname"];

    $Relationship = trim($_POST["Relationship"]);
    if(empty($Relationship)){
        $Relationship_err = "Please enter relationship.";    	
    }
    
    $Sex = trim($_POST["Sex"]);
    if(empty($Sex)){
        $Sex_err = "Please enter sex.";    	
    }
    
    $Dependent_name = trim($_POST["Dependent_name"]);
    if(empty($Dependent_name)){
        $Dependent_name_err = "Please enter a name.";
    } elseif(!filter_var($Dependent_name, FILTER_VALIDATE_REGEXP, array("options"=>array("regexp"=>"/^[a-zA-Z\s]+$/")))){
        $Dependent_name_err = "Please enter a valid name.";
    }   
    
    // Check input errors before inserting into database
    if(empty($Dependent_name_err)){
        // Prepare an update statement
        $sql = "UPDATE `DEPENDENT` SET Dependent_name=?, Relationship=?, Sex=?, Bdate = ? WHERE Essn=? AND Dependent_name = ?";
    
        if($stmt = mysqli_prepare($link, $sql)){
            // Bind variables to the prepared statement as parameters
            mysqli_stmt_bind_param($stmt, "ssssis", $param_Dependent_name, $param_Relationship, $param_Sex, $param_Bdate, $param_Ssn, $param_Dname);
            
            // Set parameters
            $param_Dependent_name = $Dependent_name;
            $param_Relationship = $Relationship;
            $param_Sex = $Sex;
            $param_Bdate = $Bdate;
            $param_Ssn = $Ssn;
            $param_Dname = $Dname;
            
            // Attempt to execute the prepared statement
            if(mysqli_stmt_execute($stmt)){
                // Records updated successfully. Redirect to landing page
                header("location: index.php");
                exit();
            } else{
                echo "<center><h2>Error when updating</center></h2>";
            }
        }        
        // Close statement
        mysqli_stmt_close($stmt);
    }
    
    // Close connection
    mysqli_close($link);
} else {

    // Check existence of sID parameter before processing further
    // Form default values
    if(isset($_GET["Ssn"]) && !empty(trim($_GET["Ssn"])) && isset($_GET["Dname"]) && !empty(trim($_GET["Dname"]))){
        $_SESSION["Ssn"] = $_GET["Ssn"];
        $_SESSION["Dname"] = $_GET["Dname"];
    
        // Prepare a select statement
        $sql1 = "SELECT * FROM DEPENDENT WHERE Dependent_name = ? AND Essn = ?";
    
        if($stmt1 = mysqli_prepare($link, $sql1)){
            // Bind variables to the prepared statement as parameters
            mysqli_stmt_bind_param($stmt1, "si", $param_Dependent_name, $param_Ssn);      
            // Set parameters
            $param_Dependent_name = trim($_GET["Dname"]);
            $param_Ssn = trim($_GET["Ssn"]);
    
            // Attempt to execute the prepared statement
            if(mysqli_stmt_execute($stmt1)){
                $result1 = mysqli_stmt_get_result($stmt1);
                if(mysqli_num_rows($result1) == 1){
    
                    $row = mysqli_fetch_array($result1);
    
                    $Dependent_name = $row['Dependent_name'];
                    $Sex = $row['Sex'];
                    $Bdate = $row['Bdate'];
                    $Relationship = $row['Relationship'];
                } else {
                    // URL doesn't contain valid id. Redirect to error page
                    header("location: error.php");
                    exit();
                }
            } else{
				echo "Error in SSN while updating";
            }
        }
            // Close statement
			mysqli_stmt_close($stmt);
        
			// Close connection
			mysqli_close($link);
    } else{
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
    <title>Update Dependent</title>
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
                        <h3>Update Record for SSN =  <?php echo $_GET["Ssn"]; ?> </H3>
                    </div>
                    <p>Please edit the input values and submit to update.
                    <form action="<?php echo htmlspecialchars(basename($_SERVER['REQUEST_URI'])); ?>" method="post">
						<div class="form-group <?php echo (!empty($Dependent_name_err)) ? 'has-error' : ''; ?>">
                            <label>Dependent Name</label>
                            <input type="text" name="Dependent_name" class="form-control" value="<?php echo $Dependent_name; ?>">
                            <span class="help-block"><?php echo $Dependent_name_err;?></span>
                        </div>
						<div class="form-group <?php echo (!empty($Relationship_err)) ? 'has-error' : ''; ?>">
                            <label>Relationship</label>
                            <input type="text" name="Relationship" class="form-control" value="<?php echo $Relationship; ?>">
                            <span class="help-block"><?php echo $Relationship_err;?></span>
                        </div>
						<div class="form-group <?php echo (!empty($Sex_err)) ? 'has-error' : ''; ?>">
                            <label>Sex</label>
                            <input type="text" name="Sex" class="form-control" value="<?php echo $Sex; ?>">
                            <span class="help-block"><?php echo $Sex_err;?></span>
                        </div>
                        <div class="form-group <?php echo (!empty($Bdate_err)) ? 'has-error' : ''; ?>">
                            <label>Birthdate</label>
                            <input type="text" name="Bdate" class="form-control" value="<?php echo $Bdate; ?>">
                            <span class="help-block"><?php echo $Bdate_err;?></span>
                        </div>						
                        <input type="hidden" name="Essn" value="<?php echo $Ssn; ?>"/>
                        <input type="submit" class="btn btn-primary" value="Submit">
                        <a href="viewDependents.php?Ssn=<?php echo $_GET["Ssn"];?>" class="btn btn-default">Cancel</a>
                    </form>
                </div>
            </div>        
        </div>
    </div>
</body>
</html>