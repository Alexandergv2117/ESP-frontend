const gateway = `ws://${window.location.hostname}/ws`;
const websocket = null;

window.addEventListener('load', onLoad);

const initWebSocket = () => {
  websocket = new WebSocket(gateway);
  websocket.onopen = onOpen;
  websocket.onclose = onClose;
  websocket.onmessage = onMessage; // <-- add this line
}

const onOpen = (event) => {
  console.log('Connection opened');
}

const onClose = (event) => {
  console.log('Connection closed');
  setTimeout(initWebSocket, 2000);
}

const onMessage = (event) => {
  const state = event.data == "1" ? 'ON' : 'OFF';
  document.getElementById('state').innerHTML = state;
}

const onLoad = (event) => {
  initWebSocket();
  initButton();
}

const initButton = () => {
  document.getElementById('button').addEventListener('click', toggle);
}

const toggle = () => {
  websocket.send('toggle');
}
