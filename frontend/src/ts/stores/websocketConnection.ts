import { writable } from 'svelte/store';
import { initWebSocket } from '../websocket';

export default writable<WebSocket>(null);