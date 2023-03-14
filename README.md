# SubTable
SubTable storage format

## About
SubTable is a storage format built for the FusionEngine for storage on-disk configuration files.

## Example file
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

## Example with the C++ parser/API
See the ```example.cpp``` file

## Characters

## ```#```
Comment

## ```?```
Create table

## ```@```
Insert key/value pair into current table
