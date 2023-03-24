<script lang="ts">
	import { sendMassage } from '../../ts/websocket';
	import { onMount } from 'svelte';
	import websocketConnection from '../../ts/stores/websocketConnection';
	function send(message: string) {
		$websocketConnection.send(message);
	}
</script>

<svelte:head>
	<title>DPAAS | Control</title>
</svelte:head>

<h1 class="text-5xl mb-3">Controller Webpage</h1>
<div class="flex space-x-4" id="wrapper">
	<div class="card w-52 bg-neutral text-neutral-content">
		<div class="card-body items-center text-center">
			<div
				class="tooltip tooltip-info tooltip-right"
				data-tip="Starts or interrupts the replacing process of the batterie"
			>
				<h1 class="card-title">Replacing process</h1>
			</div>
			<div class="card-actions justify-end">
				<div class="btn-group">
					<button
						class="btn btn-md btn-success"
						on:click={() => send('start')}>Start</button
					>
					<button
						class="btn btn-md btn-error"
						on:mousedown={() => send('stop')}>Stop</button
					>
				</div>
			</div>
		</div>
	</div>
	<div class="card w-52 bg-neutral text-neutral-content">
		<div class="card-body items-center text-center">
			<div
				class="tooltip tooltip-info tooltip-right"
				data-tip="Controls the power provided to the Steppers"
			>
				<h1 class="card-title">Stepper Power</h1>
			</div>
			<div class="card-actions justify-end">
				<div class="btn-group">
					<button
						class="btn btn-success"
						on:click={() => send('motorAn')}>On</button
					>
					<button
						class="btn btn-error"
						on:click={() => send('motorAus')}>Off</button
					>
				</div>
			</div>
		</div>
	</div>
	<button class="btn btn-primary" on:click={() => send('release')}
		>Release</button
	>
</div>
