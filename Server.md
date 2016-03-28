## <a name="server">Server</a> 
[Back to contents.](#contents)

As there are multiple users wishing to see data coming from multiple sources we needed some sort of central service that collects the information and displays it in an easy way for the users to see. 

The server acts as an API where all data is sent to and requested from. This allows us to add different visualisations very easily without the data being coupled with the interface. 

Readings that are sent to the api are processed to remove anomolous values and are scaled between 0 and 100. We then store the data in the database and it can be requested by other visualisations by making calls to the API endpoints.

There is a key which must be sent with each request to ensure that it is a device that is allowed to access that data. The request should be made over HTTPS to avoid exposing the key. The key is hardcoded into the server but can be changed by modifying the code if needed.
###<a name='server_spec'></a>API Spec
The API responds to HTTP requests which conform to [RFC2616](https://www.w3.org/Protocols/rfc2616/rfc2616-sec9.html). 

Key middleware is present throughout the API and it's responses are the following:

| Status | Response|
|--------|---------|
|403		|`{"error":{"text": The key you provided was incorrect}}`|
|401| `{"error":{"text": You did not provide a key}}`|

The endpoints are as follows:
####Readings
#####Request
|  Method | URL  |  
|---		|---|
|  POST | /api/readings  |

| Type | Params | Value |
|------|--------|-------|
| GET	|	key		| string|
|POST| 	data	| [data object](#data_object)|


#####Response
| Status | Response|
|--------|---------|
|200		|`{status:success}`|
|400| `{"error":{"text": PDO Error}}`

####<a name'data+object'></a>Data object
The data object is a csv string which contains both a timestamp and a microphone reading. It also contains the battey reading of the sensor. The csv should be formatted as shown below:

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
#####Request
|  Method | URL  |  
|---		|---|
|  get | /api/get  |

| Type | Params | Value |
|------|--------|-------|
| GET	|	key		| string|


#####Response
| Status | Response|
|--------|---------|
|200		|`{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,12,22,23,24}`|
|400| `{"error":{"text": Database Error}}`

####Get Hourly

Returns all data averages over hourly periods
#####Request
|  Method | URL  |  
|---		|---|
|  get | /api/get/hourly  |

| Type | Params | Value |
|------|--------|-------|
| GET	|	key		| string|


#####Response
| Status | Response|
|--------|---------|
|200		|
`{0:{start:183975627; end:183975687; avg: 12.4;}1:...}`|
|400| `{"error":{"text": Database Error}}`


####Get Hourly In range
Returns all data recorded between 2 given timestamps averaged over an hourly period
#####Request
|  Method | URL  |  
|---		|---|
|  get | /api/get/hourly/{start}/{end}  |

| Type | Params | Value |
|------|--------|-------|
| GET	|	key		| string|
| URI  | start	| timestamp (string)|
| URI  |end		|timestamp (string)|


#####Response
| Status | Response|
|--------|---------|
|200		|`{0:{start:183975627; end:183975687; avg: 12.4;}1:... }`|
|400| `{"error":{"text": Database Error}}`
