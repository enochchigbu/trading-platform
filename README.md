# Automated Trading Platform

This is a trading platform that leverages a **C++ backend** and a **React frontend**. The goal is to create a high-performance, reliable system for managing trades with seamless communication between the client and server.

## Tech Stack

### Frontend

- **React** (Typescript) for building the user interface.

### Backend

- **Crow** (C++ 20) for handling backend requests and API routing.

### Client Communication

- **Axios** (Typescript) for managing HTTP requests between the frontend and backend.

## Stretch Goals

1. Begin to implement the trading business logic

### Tech Debt

- Change the HTTP Post request on the backend to deprecate `JSON.Parse` on the frontend
