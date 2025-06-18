export interface IUser {
    account: string;
    password: string;
}

export interface ILoginData {
    token: string;
}

export default class User implements IUser {
    account: string = 'admin';
    password: string = 'approve123';
}