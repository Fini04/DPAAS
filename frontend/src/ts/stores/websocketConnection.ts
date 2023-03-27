import { writable } from 'svelte/store';
import { initWebSocket } from '../websocket';

export default writable<WebSocket>(initWebSocket("172.18.7.182"));