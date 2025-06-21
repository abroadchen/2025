package main

import (
	"fmt"
	"net/http"
	"net/http/httptest"
	"testing"
)

func TestCheckStatusOK(t *testing.T) {
	req, err := http.NewRequest("GET", "/CheckStatusOK", nil)
	if err != nil {
		fmt.Println(err)
		return
	}
	rr := httptest.NewRecorder()
	handler := http.HandlerFunc(CheckStatusOK)
	handler.ServeHTTP(rr, req)
	status := rr.Code
	if status != http.StatusOK {
		t.Errorf("handler returned wrong status code: got %v want %v", status, http.StatusOK)
	}
	expect := `Fine!`
	if rr.Body.String() != expect {
		t.Errorf("handler returned unexpected body: got %v want %v", rr.Body.String(), expect)
	}
}

func TestStatusNotFound(t *testing.T) {
	req, err := http.NewRequest("GET", "/StatusNotFound", nil)
	if err != nil {
		fmt.Println(err)
		return
	}
	rr := httptest.NewRecorder()
	handler := http.HandlerFunc(StatusNotFound)
	handler.ServeHTTP(rr, req)
	status := rr.Code
	if status != http.StatusNotFound {
		t.Errorf("handler returned wrong status code: got %v want %v", status, http.StatusNotFound)
	}
}
