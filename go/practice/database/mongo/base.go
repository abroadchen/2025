package mongo

import (
	"context"
	"fmt"
	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
	"go.mongodb.org/mongo-driver/mongo/readpref"
	"log"
	"time"
)

func ConnectToDB(uri, name string, timeout time.Duration, num uint64) (*mongo.Database, error) {
	ctx, cancel := context.WithTimeout(context.Background(), timeout)
	defer cancel()
	o := options.Client().ApplyURI(uri)
	o.SetMaxPoolSize(num)
	client, err := mongo.Connect(ctx, o)
	if err != nil {
		return nil, err
	}
	return client.Database(name), nil
}

func main() {
	type student struct {
		Name string
		Age  int
	}
	clientOptions := options.Client().ApplyURI("mongodb://localhost:27017")
	client, err := mongo.Connect(context.Background(), clientOptions)
	if err != nil {
		log.Fatal(err)
	}
	err = client.Ping(context.Background(), readpref.Primary())
	if err != nil {
		log.Fatal(err)
	}

	collection := client.Database("test").Collection("student")
	s1 := student{"xx", 12}
	s2 := student{"yy", 13}
	s3 := student{"zz", 14}
	insertResult, err := collection.InsertOne(context.Background(), s1)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("Inserted a single document: ", insertResult.InsertedID)
	students := []interface{}{s2, s3}
	insertManyResult, err := collection.InsertMany(context.Background(), students)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("Inserted multiple documents", insertManyResult.InsertedIDs)

	filter := bson.D{{"name", "xx"}}
	update := bson.D{
		{"$inc", bson.D{
			{"age", 1},
		}},
	}
	updateResult, err := collection.UpdateOne(context.Background(), filter, update)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("Updated one document: ", updateResult.MatchedCount, updateResult.ModifiedCount)

	var result student
	err = collection.FindOne(context.Background(), filter).Decode(&result)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("FindOne document: ", result)

	findOptions := options.Find()
	findOptions.SetLimit(3)
	var results []*student
	cur, err := collection.Find(context.Background(), bson.D{{}}, findOptions)
	if err != nil {
		log.Fatal(err)
	}
	for cur.Next(context.Background()) {
		var elem student
		err := cur.Decode(&elem)
		if err != nil {
			log.Fatal(err)
		}
		results = append(results, &elem)
	}

	for data := range results {
		fmt.Println(data)
	}

	deleteResult, err := collection.DeleteMany(context.Background(), bson.D{{}})
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("Delete documents: ", deleteResult.DeletedCount)

}
