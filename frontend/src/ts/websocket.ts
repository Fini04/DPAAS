// var gateway = `ws://${window.location.hostname}/ws`;
var websocket: WebSocket;

export function initWebSocket(ip:string) {
	console.log(`Trying to open a WebSocket connection to ${ip}`);
	websocket = new WebSocket(`ws://${ip}/ws`);

	websocket.onclose = onClose;
	websocket.onopen= onOpen;
	websocket.onmessage = onMessage;
	return websocket;
}

function onOpen(event) {
	console.log('WebSocket Connection opened');
}

function onClose(event) {
	console.log('WebSocket Connection closed');
	setTimeout(initWebSocket, 2000);
}

function onMessage(event) {
}

export function sendMassage(message:string) {
	websocket.send(message);
	console.log(message);
}