<script lang="ts">
	import Navbar from './components/Navbar.svelte';

	import Home from './components/Pages/Home.svelte';
	import Control from './components/Pages/Control.svelte';
	import Debug from './components/Pages/Debug.svelte';
	import Settings from './components/Pages/Settings.svelte';

	import activePage, { Pages } from './ts/stores/activePage';
</script>

<main class="p-4">
	<Navbar />
	{#if $activePage === Pages.home}
		<Home />
	{/if}
	{#if $activePage === Pages.control}
		<Control />
	{/if}
	{#if $activePage === Pages.debug}
		<Debug />
	{/if}
	{#if $activePage === Pages.settings}
		<Settings />
	{/if}
</main>
