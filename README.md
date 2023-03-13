# SubTable
SubTable storage format

## About
SubTable is a storage format built for the LambdaEngine for storage on-disk configuration files.
This example parser dumps the output to XML

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

## Characters

## ```#```
Comment

## ```?```
Create table

## ```@```
Insert key/value pair into current table
