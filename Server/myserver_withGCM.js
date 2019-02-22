const express = require('express');
const gcm = require('node-gcm');
const mysql = require('mysql');
const bodyParser = require('body-parser');
const app = express();

app.use(bodyParser.json());

const sender = new gcm.Sender('ENTER LEGACY SERVER KEY HERE');
const regTokens = ['ENTER THE TOKEN GENERATED IN ANDROID STUDIO LOGS ON FIRST INSTALLATION HERE'];
 

app.get("/cart",(request,response)=>{

//Creating connction object for mysql
const connection = mysql.createConnection({
        host: 'localhost', user: 'DB_USERNAME', password: 'DB_PASSWORD', database: 'DATABASE_NAME'
    });					

//Connecting above connection object with mysql
 connection.connect();

//creating a query to fire on my mysql database
 const myquery = "select value from table_direction where id = 1";

//Executing our query on our mysql database
var value = {};
 connection.query(myquery, (error, result) => {
console.log(error);
//closing my resource
connection.end();
//result["status"]="success";
value["data"]=result;
console.log(value);
response.send(value);
 });


});

app.get("/cart/:value",(request,response)=>{

//Creating connction object for mysql
const connection = mysql.createConnection({
        host: 'localhost', user: 'DB_USERNAME', password: 'DB_PASSWORD', database: 'DB_NAME'
    });					

//Connecting above connection object with mysql
 connection.connect();
    var message;
    var myquery = 100; //some value other than 0,1,2,3,4
    var value =request.params.value;
if ((value == 1) || (value == 2) || (value ==3) || (value ==4) || (value == 0)){
    if(value == 0){
        message = new gcm.Message({
            data: {
                "value": "0"
            }
        });
    } else if(value == 1){
        message = new gcm.Message({
            data: {
                "value": "1"
            }
        });
    } else if(value == 2){
        message = new gcm.Message({
            data: {
                "value": "2"
            }
        });
    } else if(value == 3){
        message = new gcm.Message({
            data: {
                "value": "3"
            }
        });
    } else if(value == 4){
        message = new gcm.Message({
            data: {
                "value": "4"
            }
        });
    }


    // create the query
    myquery = `update table_direction set value = "${value}";`;
     // execute the query
     connection.query(myquery, (error, result) => {
        // close the connection
console.log(error);
        connection.end();

        
    });

    console.log('sending message');
    sender.send(message, { registrationTokens: regTokens }, function (err, responseMessage) {
        console.log('message sent');

        if (err) console.error(err);
        else console.log(responseMessage);

        response.send('Value updated');
    });

} else{
    response.send('Invalid URL');
}
});

            
app.listen(4500, '0.0.0.0', () => {         //Port Number and URL 0.0.0.0 will take default IP Address
    console.log('server started on port 4500');
});