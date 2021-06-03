var mysql = require('mysql');
var pool = mysql.createPool({
  connectionLimit : 10,
  host            : 'classmysql.engr.oregonstate.edu',
  user            : 'cs340_mohrna',
  password        : '3202',
  database        : 'cs340_mohrna'
});
module.exports.pool = pool;
