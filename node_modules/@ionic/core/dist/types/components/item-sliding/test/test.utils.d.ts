import type { Locator } from '@playwright/test';
import type { E2EPage } from '@utils/test/playwright';
export declare const testSlidingItem: (page: E2EPage, item: Locator, screenshotNameSuffix: string, openStart?: boolean) => Promise<void>;
