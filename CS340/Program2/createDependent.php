<?php
// Include config file
session_start();
require_once "config.php";
$Ssn = $_SESSION["Ssn"];

$Dependent_name = $Sex = $Bdate = $Relationshp = "";
$Dependent_name_err = $Sex_err = $Birth_err = $Relationshp_err = "";

// Processing form data when form is submitted
if($_SERVER["REQUEST_METHOD"] == "POST"){
    // Validate Name
    $Dependent_name = trim($_POST["Dependent_name"]);
    if(empty($Dependent_name)){
        $Dependent_name_err = "Please enter a Dependent_name.";
    } elseif(!filter_var($Dependent_name, FILTER_VALIDATE_REGEXP, array("options"=>array("regexp"=>"/^[a-zA-Z\s]+$/")))){
        $Dependent_name_err = "Please enter a valid Dependent_name.";
    } 

    // Validate Sex
    $Sex = trim($_POST["Sex"]);
    if(empty($Sex)){
        $Sex_err = "Please enter Sex.";     
    }
	// Validate Birthdate
    $Bdate = trim($_POST["Bdate"]);
    if(empty($Bdate)){
        $Birth_err = "Please enter birthdate.";     
    }	

	// Validate Department
    $Relationship = trim($_POST["Relationship"]);
    if(empty($Relationship)){
        $Relationship_err = "Please enter a relationship.";     		
	}

    // Check input errors before inserting in database
    if(empty($Dependent_name_err) && empty($Sex_err) && empty($Birth_err) && empty($Relationship_err)){
        $sql = "INSERT INTO `DEPENDENT` (Essn, Dependent_name, Sex, Bdate, Relationship) 
		        VALUES (?, ?, ?, ?, ?)";
        if($stmt = mysqli_prepare($link, $sql)){
            // Bind variables to the prepared statement as parameters
            mysqli_stmt_bind_param($stmt, "issss", $param_Ssn, $param_Dependent_name, $param_Sex, $param_Bdate, $param_Relationship);
            
            // Set parameters
            $param_Ssn = $Ssn;
            $param_Dependent_name = $Dependent_name;
            $param_Sex = $Sex;
            $param_Bdate = $Bdate;
            $param_Relationship = $Relationship;
            
            // Attempt to execute the prepared statement
            if(mysqli_stmt_execute($stmt)){
                // Records created successfully. Redirect to landing page
                    header("location: index.php");
                    exit();
            } else{
                echo "<center><h4>Error while creating new employee</h4></center>";
                $Ssn_err = "Enter a unique Ssn.";
            }
        }
            
        // Close statement
        mysqli_stmt_close($stmt);
    }
    // Close connection
    mysqli_close($link);
}
?>
 
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Create a Dependent</title>
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
                        <h2>Create a Dependent</h2>
                    </div>
                    <h4>Employee SSN =  <?php echo $Ssn; ?> </h4>
                    <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post">
                 
						<div class="form-group <?php echo (!empty($Dependent_name_err)) ? 'has-error' : ''; ?>">
                            <label>Dependent's Name</label>
                            <input type="text" name="Dependent_name" class="form-control" value="<?php echo $Depenedent_name; ?>">
                            <span class="help-block"><?php echo $Dependent_name_err;?></span>
                        </div>
				
						<div class="form-group <?php echo (!empty($Sex_err)) ? 'has-error' : ''; ?>">
                            <label>Sex</label>
                            <input type="text" name="Sex" class="form-control" value="<?php echo $Sex; ?>">
                            <span class="help-block"><?php echo $Sex_err;?></span>
                        </div>
						                  
						<div class="form-group <?php echo (!empty($Birth_err)) ? 'has-error' : ''; ?>">
                            <label>Birth date</label>
                            <input type="date" name="Bdate" class="form-control" value="<?php echo date('Y-m-d'); ?>">
                            <span class="help-block"><?php echo $Birth_err;?></span>
                        </div>

                        <div class="form-group <?php echo (!empty($Relationship_err)) ? 'has-error' : ''; ?>">
                            <label>Relationship</label>
                            <input type="text" name="Relationship" class="form-control" value="<?php echo $Relationship; ?>">
                            <span class="help-block"><?php echo $Relationship_err;?></span>
                        </div>
                        <input type="hidden" name="Ssn" value="<?php echo $Ssn; ?>"/>
                        <input type="submit" class="btn btn-primary" value="Submit">
                        <a href="viewDependents.php?Ssn=<?php echo $_GET["Ssn"];?>" class="btn btn-default">Cancel</a>
                    </form>
                </div>
            </div>        
        </div>
    </div>
</body>
</html>