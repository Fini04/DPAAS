import { writable } from 'svelte/store';

export enum Pages {
	home,
	control,
    debug,
	settings,
}

export default writable<Pages>(Pages.home);