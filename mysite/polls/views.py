from django.shortcuts import render

# Create yor views here
from django.http import HttpResponse
def index(request):
	return HttpResponse("Hello , world.Polls\n")

