# SubTable
SubTable storage format

## Example format
```
# SubTable example file
# In order for a parser to work it must be able to parse this file 

?Test {
  @Port = 8080
  
  ?OtherTable {
    @Port = 5959
  }
}
```

## Characters

## ```#```
Comment

## ```?```
Create table

## ```@```
Insert key/value pair into current table
