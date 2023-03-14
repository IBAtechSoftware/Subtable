# SubTable example file
# In order for a parser to work it must be able to parse this file 

?Test {
  @Port = 8080
  @EnableHttps = true
  @Users = [user1, user2]
  
  ?OtherTable {
    @OtherValue = 5959
    @OtherBool = false
  }
}
