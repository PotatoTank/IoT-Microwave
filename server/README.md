# LocalServer
A localserver we wrote in like 5 minutes (~30 minutes before our demo) that exposes Serial data being transmitted over USB.

## Purpose
The purpose of this is to expose serial data, so that the local player page can determine what buttons are being pressed.

## Usage
Clone the repository, then run

```bash
npm install
npm start
```

This should open a webserver on port ``3000``, and listen for serial data on ``COM3``.
