The project implement the Personal Diary. There is a database to store all the diary, and the database and the operations to the diary is in the class 'CLI'. The program read the instruction and do certain operation.
No multiple files and just run with g++.
The input format of each programs are as follows:
- pdadd: add an entity
year/month/day    // date of diary
content of the diary
end with '.' in a line or EOF

- pdlist: list all the diary needed
pdlist  // list all the diary in the database
pdlist [start_date, end_date]  // list the diary among the range

- pdshow: show the content in the date
pdshow date  // if the key is in the database, output the value, else output "No found"

- pdremove: remove certain entity
pdremove date // if the key is in the database, remove and return 0, else output "No found" and return -1