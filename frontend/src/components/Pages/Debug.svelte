<script lang="ts">
	import { onMount } from 'svelte';
	import websocketConnection from '../../ts/stores/websocketConnection';
	// let state = 'np current data';
	// onMount(() => {
	// 	$websocketConnection.addEventListener('message', function (e) {
	// 		state = e.data;
	// 	});
	// });
	function send(message: string) {
		$websocketConnection.send(message);
	}
</script>

<svelte:head>
	<title>DPAAS | Debug</title>
</svelte:head>

<div id="wrappers">
	<h1 class="text-5xl mb-3">Debug</h1>

	<div class="flex flex-wrap gap-4">
		<div class="card w-52 bg-neutral text-neutral-content">
			<div class="card-body items-center text-center">
				<div
					class="tooltip tooltip-info"
					data-tip="Controls the movement of the y-axis manualy"
				>
					<h1 class="card-title">Y-axis</h1>
				</div>
				<div class="card-actions justify-end">
					<div class="btn-group">
						<button
							class="btn btn-primary"
							on:mousedown={() => send('yVor')}
							on:mouseup={() => send('stop')}>Vor</button
						>
						<button
							class="btn btn-primary"
							on:mousedown={() => send('yZuruck')}
							on:mouseup={() => send('stop')}>Zurück</button
						>
					</div>
				</div>
			</div>
		</div>
		<div class="card w-52 bg-neutral text-neutral-content">
			<div class="card-body items-center text-center">
				<div
					class="tooltip tooltip-info"
					data-tip="Controls the movement of the x-axis manualy"
				>
					<h1 class="card-title">X-axis</h1>
				</div>
				<div class="card-actions justify-end">
					<div class="btn-group">
						<button
							class="btn btn-primary"
							on:mousedown={() => send('xVor')}
							on:mouseup={() => send('stop')}>Vor</button
						>
						<button
							class="btn btn-primary"
							on:mousedown={() => send('xZuruck')}
							on:mouseup={() => send('stop')}>Zurück</button
						>
					</div>
				</div>
			</div>
		</div>
		<div class="card w-52 bg-neutral text-neutral-content">
			<div class="card-body items-center text-center">
				<div
					class="tooltip tooltip-info"
					data-tip="Controls the movement of the magazin manualy"
				>
					<h1 class="card-title">Magazin</h1>
				</div>
				<div class="card-actions justify-end">
					<div class="btn-group">
						<button
							class="btn btn-primary"
							on:mousedown={() => send('magVor')}
							on:mouseup={() => send('stop')}>Vor</button
						>
						<button
							class="btn btn-primary"
							on:mousedown={() => send('magZuruck')}
							on:mouseup={() => send('stop')}>Zurück</button
						>
					</div>
				</div>
			</div>
		</div>
		<div class="card w-52 bg-neutral text-neutral-content">
			<div class="card-body items-center text-center">
				<div
					class="tooltip tooltip-info"
					data-tip="Controls the movement of the arm manualy"
				>
					<h1 class="card-title">Arm</h1>
				</div>
				<div class="card-actions justify-end">
					<div class="btn-group">
						<button
							class="btn btn-primary"
							on:mousedown={() => send('armVor')}
							on:mouseup={() => send('stop')}>Vor</button
						>
						<button
							class="btn btn-primary"
							on:mousedown={() => send('armZuruck')}
							on:mouseup={() => send('stop')}>Zurück</button
						>
					</div>
				</div>
			</div>
		</div>
		<div class="card w-52 bg-neutral text-neutral-content">
			<div class="card-body items-center text-center">
				<div
					class="tooltip tooltip-info"
					data-tip="Controls state of the gripper"
				>
					<h1 class="card-title">Gripper</h1>
				</div>
				<div class="card-actions justify-end">
					<div class="btn-group">
						<button
							class="btn btn-primary"
							on:mousedown={() => send('Grab')}
							on:mouseup={() => send('stop')}>Grab</button
						>
						<button
							class="btn btn-primary"
							on:mousedown={() => send('Release')}
							on:mouseup={() => send('stop')}>Release</button
						>
					</div>
				</div>
			</div>
		</div>
		<button
			class="btn btn-error"
			on:mousedown={() => send('stop')}
			on:mouseup={() => send('stop')}>Stop</button
		>
	</div>

	<h1>Function test</h1>
	<div class="flex gap-4 flex-wrap">
		<!-- <button class="btn" on:click={() => send('toggle')}>Toggle</button> -->
		<button class="btn" on:click={() => send('callibrate')}
			>Callibrate</button
		>
		<button class="btn" on:click={() => send('motorAus')}>Motor Aus</button>
		<button class="btn" on:click={() => send('motorAn')}>Motor An</button>
		<button class="btn" on:click={() => send('grab')}>Grab</button>
		<button class="btn" on:click={() => send('release')}>Release</button>
		<button class="btn" on:click={() => send('armReinSchieben')}
			>Arm reinschieben</button
		>
		<button class="btn" on:click={() => send('armRausZiehen')}
			>Arm rausziehen</button
		>
		<button class="btn" on:click={() => send('akkuLeer')}>Akku leer</button>
		<button class="btn" on:click={() => send('akkuVoll')}>Akku voll</button>
		<!-- <button class="btn" on:click={() => send('getStepPos')}
			>getStepPos</button
		> -->
	</div>
	<!-- <div>{state}</div> -->
</div>
