# Ken Rodriguez
# CS340
# Python code using 'CRUD' to create read, update, and delete documents
# from the AAC database

#Example Python Code to Insert a Document
from pymongo import MongoClient
from bson.objectid import ObjectId

class AnimalShelter(object):
    #""" CRUD operations for Animal collection in MongoDB """

    def __init__(self,username,passw):
        # Initializing the MongoClient. This helps to 
        # access the MongoDB databases and collections. 
        # set database to the AAC database to access the animals collection
        self.client = MongoClient('mongodb://%s:%s@localhost:38926/?authMechanism=DEFAULT&authSource=AAC' % (username, passw))

        # alternate starter w/o username and password
        #self.client = MongoClient('mongodb://localhost:38926')
        
        # set database for use
        self.database = self.client['AAC']

        
# Complete this create method to implement the C in CRUD.
    def create(self, data):
        if data is not None:
            self.database.animals.insert(data)  # data should be dictionary
            return('Success')
        else:
            raise Exception("Nothing to save, because data parameter is empty")

            
# Create method to implement the R in CRUD. 
    # read ONE
    def read(self, data):
        # if data is present and not None, attempt to read data.
        # if data read is successful, return the result of the findOne query.
        if data is not None:
            cursor = self.database.animals.find_one(data)
            return cursor
        else:
            raise Exception("Nothing to read because data parameter isn't formatted properly")
    
    # read ALL
    def readAll(self, data):
        cursor  = self.database.animals.find(data,{"_id":False})
        return cursor
    
    
# Create method to implement the U in CRUD
    # UPDATE
    def update(self, oldData, newData):
        # if the text that's going to be updated TO is not NONE, execute
        if oldData is not None:
            if newData:
                result = self.database.animals.update_one(oldData, {"$set":newData})
                return result
        else:
            raise Exception("Nothing to update because parameter isn't formatted properly")
    
    
# Create method to implement the D in CRUD
    # DELETE
    def delete(self, data):
        # if the entry that's going to be deleted isn't present, execute
        if data is not None:
            if data:
                result = self.database.animals.delete_one(data)
                return result
            else:
                raise Exception("Nothing to delete because parameter isn't formatted properly")
            