import ScanbotSdk, { Page } from "cordova-plugin-scanbot-sdk";

export class ImageResultsRepository {

    public static INSTANCE = new ImageResultsRepository();

    private pages: Page[] = [];

    public getPages(): Page[] {
        return this.pages;
    }

    public getPageById(id: string) {
        return this.pages.find(p => p.pageId === id);
    }

    public async addPages(pages: Page[]) {
        this.pages = this.pages.concat(pages);
    }

    public async updatePage(page: Page) {
        let replaced = false;
        for (let i = 0; i < this.pages.length; ++i) {
            if (this.pages[i].pageId === page.pageId) {
                this.pages[i] = page;
                replaced = true;
                break;
            }
        }
        if (!replaced) {
            this.pages.push(page);
        }
    }

    public async removePage(page: Page) {
        const index = this.pages.findIndex(p => p.pageId === page.pageId);
        if (index > -1) {
            this.pages.splice(index, 1);
        }
    }

    public async removeAllPages() {
        this.pages = [];
    }

    public fetchDataFromUri(path: string) {

        let imageData: string;

        ScanbotSdk.getImageData((result) => {

            const extension = 'png';

            return imageData = `data:image/${extension};base64,` + result.base64ImageData;

        },
        () => { },
        { imageFileUri: path }); 
    } 
}