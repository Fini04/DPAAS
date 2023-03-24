<script lang="ts">
	import activePage from '../ts/stores/activePage';
	function goTo(x: number) {
		$activePage = x;
	}
</script>

<nav class="navbar bg-base-300 rounded-box mb-4">
	<div class="flex-1 px-2 lg:flex-none">
		<h1 class="text-lg font-bold">
			<span class="transition-all duration-500 hover:text-green-500"
				>DPAAS</span
			>
			<div class="hidden lg:inline">
				-
				<span class="transition-all duration-500 hover:text-green-500"
					>D</span
				>rohnen
				<span class="transition-all duration-500 hover:text-green-500"
					>P</span
				>ositionierungs und
				<span class="transition-all duration-500 hover:text-green-500"
					>A</span
				>kku
				<span class="transition-all duration-500 hover:text-green-500"
					>A</span
				>ustausch
				<span class="transition-all duration-500 hover:text-green-500"
					>S</span
				>ystem
			</div>
		</h1>
	</div>
	<div class="flex justify-end flex-1 px-2">
		<div class="flex space-x-2 items-stretch">
			<button class="btn btn-outline btn-primary" on:click={() => goTo(0)}
				>Home</button
			>
			<button class="btn btn-outline btn-primary" on:click={() => goTo(1)}
				>Control</button
			>
			<button class="btn btn-outline btn-primary" on:click={() => goTo(2)}
				>Debug</button
			>
			<button class="btn btn-outline btn-accent" on:click={() => goTo(3)}
				>Settings</button
			>
		</div>
	</div>
</nav>
