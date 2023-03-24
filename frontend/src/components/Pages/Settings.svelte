<script lang="ts">
	import { initWebSocket } from '../../ts/websocket';
	let ip = '192.168.0.0';
	function init() {
		initWebSocket(ip);
	}
</script>

<svelte:head>
	<title>DPAAS | Settings</title>
</svelte:head>

<div>
	<h1 class="text-5xl mb-3">Websocket</h1>
	<label class="label" for="test">websocket adress:</label>
	<label class="input-group">
		<span>IP:</span>
		<input
			class="input input-primary"
			name="test"
			bind:value={ip}
			type="text"
		/>
		<button class="btn btn-primary" on:click={init}>connect</button>
	</label>
</div>
