## Server
[Back to contents.](#contents)


###Description

As there are multiple users wishing to see data coming from multiple sources we needed some sort of central service that collects the information and displays it in an easy way for the users to see. 

The server acts as an API where all data is sent to and requested from. This allows us to add different visualisations very easily without the data being coupled with the interface. We then store the data in the database and it can be requested by other visualisations by making calls to the API endpoints.

There is a key which must be sent with each request to ensure that it is a device that is allowed to access that data. The request should be made over HTTPS to avoid exposing the key. The key is hardcoded into the server but can be changed by modifying the code if needed.

To get a development server running first install a copy of [Laravel homested](https://laravel.com/docs/5.2/homestead). Run through the setup guide and clone the repository into the specified directory. After this you can run need to insure all dependancies are installed by running `composer install && bower install`. After this you can run `homestead up` and visit the address you specified in the homestead setup.

As the server is using Laravel you can easily set up the databases without manually running SQL queries.

In the root directory of the app you can run the following command to create all of the database tables.

`php artisan migrate`

This creates tables based on a model definition, an example definition can be seen below: 

```php
class CreateUsersTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('users', function (Blueprint $table) {
            $table->increments('id');
            $table->string('name');
            $table->string('email')->unique();
            $table->string('password');
            $table->string('phone');
            $table->rememberToken();
            $table->timestamps();
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::drop('users');
    }
}

```
This uses the built in 'schema builder' to turn the php code into sql which is then run on the database.


###API Spec
The API responds to HTTP requests which conform to status codes set out in [RFC2616](https://www.w3.org/Protocols/rfc2616/rfc2616-sec9.html). 

Key middleware is present throughout the API and it's responses are the following:

| Status | Response|
|--------|---------|
|403		|`{"error":{"text": The key you provided was incorrect}}`|
|401| `{"error":{"text": You did not provide a key}}`|

The endpoints are as follows:
####Readings
*Request*

|  Method | URL  |  
|---		|---|
|  POST | /api/readings  |

| Type | Params | Value |
|------|--------|-------|
| GET	|	key		| string|
|POST| 	data	| [data object](#data_object)|


*Response*

| Status | Response|
|--------|---------|
|200		|`{status:success}`|
|400| `{"error":{"text": PDO Error}}`|

<a name'data+object'></a>
####Data object
The data object is a csv string which contains both a timestamp and a microphone reading. It also contains the battery reading of the sensor. The csv should be formatted as shown below:

```
'id',id
timestamp,reading
'batt', battery_percentage
```
example with values:

```
id, 2
14073748529, 3547
14073748530, 3047
14073748531, 3538
batt, battery_percentage
```

Please ensure all lines are separated with \n\r

####Get
Returns 24 hours worth of data averaged over one hour periods
*Request*

|  Method | URL  |  
|---		|---|
|  get | /api/get  |

| Type | Params | Value |
|------|--------|-------|
| GET	|	key		| string|


*Response*

| Status | Response|
|--------|---------|
|200		|`{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,12,22,23,24}`|
|400| `{"error":{"text": Database Error}}`

####Get Hourly

Returns all data averages over hourly periods
*Request*

|  Method | URL  |  
|---		|---|
|  get | /api/get/hourly  |

| Type | Params | Value |
|------|--------|-------|
| GET	|	key		| string|


*Response*

| Status | Response|
|--------|---------|
|200		|`{0:{start:183975627; end:183975687; avg: 12.4;}1:...}`|
|400| `{"error":{"text": Database Error}}`


####Get Hourly In range
Returns all data recorded between 2 given timestamps averaged over an hourly period.
*Request*

|  Method | URL  |  
|---		|---|
|  get | /api/get/hourly/{start}/{end}  |

| Type | Params | Value |
|------|--------|-------|
| GET	|	key		| string|
| URI  | start	| timestamp (string)|
| URI  |end		|timestamp (string)|


*Response*

| Status | Response|
|--------|---------|
|200		|`{0:{start:183975627; end:183975687; avg: 12.4;}1:... }`|
|400| `{"error":{"text": Database Error}}`

#### MVC
The server is built using the MVC layout which allows for decoupling of elements and helps to make the structure understandable. As seen in the diagram below, data mainly flows one way.

![](Images/visualisation/mvc.png)

In the server, the views are very minimal as it is mainly just displaying json data. While the views aren't the same as in most applications, they still work in the same way.

The server has three main models:

- Device: This represents a physical device and stores things such as battery level and name
- Reading: This is a data reading and links to a Device. It contains the raw data and timestamps
- User: This stores the users details such as email, phone number and password

These are all called by the controllers who then pass the data straight onto the views to display it.

###Previous Work

####Iteration 1 - Initial Work
***At this point we had thought visualisation and back end server were the same thing. This was later changed but for documentation purposes we have considered the initial itererations of this as part of the server***

As there are multiple users wishing to see data coming from multiple sources there needs to be some kind of central service that collects the information and displays it in an easy way for the users to see. 

One option for this is to use the hubs themselves as servers. This means that there would be no extra hardware required and everything to run the system would be in the user’s home. This poses several problems, one of which is that the hardware is in the user’s home so if something were to go wrong with the software and it were to crash the device would require a restart on the user’s end which would mean either asking them or going into their house. During this time there would be no results being received by the server and  you would not be able to view any previous results. It also means asking the hub device to do multiple things which means there are more things that could go wrong.

Another option is to have this service run on the university’s servers, this approach also has several pros and cons. One of the benefits is that all the infrastructure and software to run a server and databases are in place and we would simply have to ask for one to be set up. Another good thing about using the university’s infrastructure is that we have greater control and there are safeguards already in place for if things go wrong. One downside to this method is that currently, to access the servers, you need to be connected to the University’s network by being on campus or over VPN. This could be a big problem as the the devices will not be located on campus and ideally would not be connected to the VPN as it can become complex and is yet another thing that could go wrong. One way around this that has been suggested is to use the server that The Shed has. We have been told by Dan Knox that it would be possible to open up some of the ports on that server to allow connections from outside the University’s network.

Overall the option of having a web server in the university would be the best option as it is already provided as a service and is maintained so there would be less maintenance for this project. This decision is relies on being able to open up the sheds servers for outside connections. If it turns out this is not possible then we will have to revisit the hub/server idea and possibly think of some other options.

#####What we need
The basic idea of the web end of this project is to provide a place to store large amounts of data over a large period of time and have some sort of mechanism where the user can see those results in a meaningful way. The devices/hubs also need to be able to connect to this service so they can send results directly to it. The user also needs to be made aware of device status such as whether the battery is running low or the device has crashed and needs restarting. This means that the main requirements of the web service are as follows:

- Provide an interface the hubs can easily talk to
- Have the ability to store large amounts of data, around 2.5 million records per year (365 days * 24 hours * 60 minutes * 5 devices which is a reading every minute)
- Show the information that has been collected in a meaningful way that makes sense to the user.
- Provide users with notifications, in the form of emails, regarding the status of devices
- Be easily maintainable as it may need to be picked up by other developers in the future
- Process data. The data sent from the hub will be the raw data from the sensors. The web service needs to turn these into meaningful values and store those

#####Technologies
######Database Comparison
One thing that the web end will definitely need is a database to store all of the data that it is being sent from the sensors. There are many different types of database that are available but we narrowed it down to just three based on what we had experience with and were comfortable using in a short space of time. These three are mongodb, PostgreSQL and MySQL.

*MongoDB*

MongoDB is a NoSQL database that has not defined structure. You can add and remove fields in each record as you see fit. It also favours a high insert rate over a high read rate which is what our application would be doing as a majority of the work would be coming from the sensors rather than people wanting to view the data. The variable structure of this database would make it easier to add sensors going forwards however even though there is no explicit structure in the database itself it would just move the structure over to the web app instead. This means that the web app know what data is stored where and where relations between it should be. This means more time has to be spent on the web app to make sure the structure makes sense. There would still need to be many changes made on the app side if a new sensor type was introduced. Also, as it is a relatively new technology the documentation is not ideal and it is harder to pick up than a standard relational database if you have never worked with NoSQL before. 

*PostgreSQL*

Postgres is a fully features RDBMS that is widely used and growing in popularity. There is a large community around Postgres meaning there are a lot of blog and knowledgebase style articles that provide a lot of support and make development easier. One of the disadvantages is that it provides a lot of functionality that will be unused for simple reads and writes which is what this application will be doing. A benefit of postgres is that it is provided by the university and can be set up by someone outside the project.

*MySQL*

MySQL is another RDBMS and is the most popular one. One advantage of MySQL is that it is very easy to pick up and get started with as it only provides a limited set of features. This could be a downside but it provides everything that this application would need. It is slightly faster than Postgres and there is a lot of support on the internet for it. It is also something that can be set up and maintained by the university.


All of these databases can handle large amounts of data >20 million records which means they are all suitable for the volume of data that will be necessary for this project.

######Language
Because the application needs to run on a server, it needs to be written in a language that a server can be easily set up to understand. PHP was chosen for this as it was a language that everyone in the group is familiar with and has had previous experience using. PHP also fits all of the requirements and is very well documented. 

######MVC Frameworks
Frameworks are tools that are designed to make the development of applications easier by providing a set structure and providing some commonly used features such as authentication. This means that there is less time spent re inventing the wheel and more time can be spent on application specific code. The decision to use a framework was made as one of the key requirements is maintainability. Frameworks provide a lot of documentation to make understanding them very easy. To create something that was tested and documented to the level of an existing framework would take a long time and we felt we could better spend this time in other areas such as UI development. 

Several frameworks were looked at: 

*Laravel*

Laravel is an open source MVC PHP framework. Laravel provides a lot of features out of the box such as an ORM (used for creating and maintaining relationships in databases), a templating engine, database migrations (used to control the structure of your database) and range of other packages handling things such as payment and social logins that can be easily implemented. A benefit of this framework is that it could be very easily extended to add complex features with very little effort and development time. Another good thing about Laravel is that the documentation is well maintained and is regularly updated.

One downside is that it does a lot of things that are simply not necessary for this project. These unnecessary features increase the learning curve of this framework even though it can make things easier in the long run.


*Slim*

Slim is a simple PHP framework that is often used for simple web apps and apis.  It doesn’t provide some of the more advanced features that laravel does but it does give you things such as routing, middleware (for things such as authentication), and easy http manipulation methods.

One downside to Slim is that it is not hugely popular so there are less tutorials and help threads for it but it does have it’s own set of well maintained documentation which means this isn’t a huge issue. 

A benefit is that it doesn’t try to do everything for you, just a core set of things which means it’s easy to pick up and requires very little time to understand. This is key for the maintainability part of the requirements. It also gives you the ability to create simple views to display data without having to learn another templating language, it does it all in PHP.  

*CodeIgniter*

CodeIgniter is another widely used MVC framework that provides a lot of features straight out of the box. As with Laravel, the downside to this is that there is a lot to learn and it’s not instantly obvious what is going on. One of it’s main advantages is its speed compared to other large frameworks however this is less of an advantage when comparing it to lighter frameworks such as slim. It also has a very active community which means documentation is readily available and kept updated.

*Conclusion*

After looking at the different frameworks that were available to us we decided that the best one to use was Slim due to its simple nature. It meant that we could all pick it up fast and get working quickly while still having good documentation that would be easy for anyone else to pick up.

######Version Control
Version control was necessary for this projects as it provided a log of what had been done which we could revert back to if anything went wrong. It also allowed us all to view the code so it could be looked over to check what was being written and committed was sane.We decided to use git for version control as it is an industry standard and we all had some experience of using it. We are hosting the remote repository on Github as it provides an easy to use interface and also allows transfer of repository ownership should someone else wish to take the project on in future. 

##### Outcome of Iteration
We produced a system that would take data it received from requests and store it in a database. This system ran in a local development environment so was no accessible outside of the computer it was running on. It also showed pages that displayed basic data such as a table of timestamps and readings. This was written using the slim framework


#### Iteration 2 - Splitting Front and Back End

##### Issues with previous iteration

During the previous iteration we discussed putting the application on the university servers however this hasn't been set up so we have used a temporary sever that we are hosting ourselves using digital ocean. The server is using the same technologies as previously mentioned and is running on ubuntu 14.04. 

Another issue we became aware of after the implementation of the first iteration was that the data and the views were very tightly coupled together. We then decided that it would benefit the project to split the front end and back end up into two separate parts. The server would act as an API and the front end would be used to display the data. This would allow us to add the 'clock', which we weren't aware of at the beginning, to the system without any major issues.


#####Outcome of iteration
We worked to split the front end code from the API and the front end so that they could work independently without duplication of code. We realised some kind of security was also needed so we added key based authentication to provide a basic level of security. 

#### Iteration 3 - Switching Frameworks

##### Issues with previous iteration
After we split the front and backend we realised we were going to be using slim to server the backend and Laravel to serve the front end. This would mean using someone who was picking this up would have to learn multiple frameworks.

##### Result of iteration
We decided to change the backend the also use laravel to make the system easier to pick up. Most of our code was easily portable as they use the same language and roughly the same MVC layout. 

#### Iteration 4
#####Issues with previous iteration
While working on the visualisation we discovered that filtering on the client side was not an option as it took too long to load. This meant that we had to do averaging and filtering on the server side. This was due to loading large amounts of raw data. For example to visualise 1 month worth of dummy data it was having to load ~600,000 (60\*24\*7*4) readings which took a considerable amount of time. It then had to group this data and calculate averages based on this which, again, increased page load time. The total load time of a page loading this amount of data was ~6 seconds

The sensor was also struggling to create json arrays due to memory limitations. This meant that the format the server was expecting was often not the format it received. 

#####Outcome of iteration
We changed the format of data being sent to and from the sensor from JSON to CSV. This meant there was less overhead in generating the data on the sensors and also less overhead when receiving data.

We moved a majority of the data processing over to the server rather than the client. This was mainly done by using SQL queries to group and average the data. As this is what the database engine is designed for it was able to considerably speed up this process.

Server code can be found [here](visualisation/web/)

More information on the framework used and where the main files are located can be found at the [laravel website](https://laravel.com/docs/master)
